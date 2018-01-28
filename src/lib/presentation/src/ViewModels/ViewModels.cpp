#include <QtCore/QThread>
#include <MellowPlayer/Presentation/ViewModels/ViewModels.hpp>

using namespace MellowPlayer::Presentation;

ViewModels::ViewModels(ApplicationViewModel&,
                       IMainWindow& mainWindow,
                       SettingsViewModel&,
                       ThemeViewModel&,
                       UpdaterViewModel& updater,
                       ListeningHistoryViewModel& listeningHistory,
                       StreamingServicesViewModel& streamingServices,
                       IContextProperties& contextProperties)
        : mainWindow_(mainWindow),
          updater_(updater),
          listeningHistory_(listeningHistory),
          streamingServices_(streamingServices),
          cache_(contextProperties),
          cookies_(contextProperties),
          clipboard_(contextProperties),
          devToolsWindow_(contextProperties)
{

}

void ViewModels::initialize()
{
    cache_.clear();
    streamingServices_.initialize();
    listeningHistory_.initialize();
    mainWindow_.load();
    updater_.check();
}

void ViewModels::cleanup()
{
    cache_.clear();
}
