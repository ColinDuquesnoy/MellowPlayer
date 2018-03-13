#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Presentation;

CookiesViewModel::CookiesViewModel(IContextProperties& contextProperties)
        : ContextProperty("_cookies", this, contextProperties)
{

}

void CookiesViewModel::clear()
{
    QWebEngineProfile profile("Default");
    QDir storageDir(profile.persistentStoragePath());
    qDebug() << "removing persistent storage directory: " << storageDir;
    storageDir.removeRecursively();
}
