#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <QtCore/QDebug>

using namespace MellowPlayer::Presentation;

CacheViewModel::CacheViewModel(IContextProperties& contextProperties)
        : ContextProperty("_cache", this, contextProperties)
{

}

void CacheViewModel::clear()
{
    // clear http cache
    QWebEngineProfile profile("Default");
    profile.clearHttpCache();

    // clear mellowplayer cache (covers,...)
    for (auto dir: QStandardPaths::standardLocations(QStandardPaths::CacheLocation))
    {
        QDir cacheDir(dir);
        qInfo() << "removing cache directory: " << dir;
        cacheDir.removeRecursively();
    }
}
