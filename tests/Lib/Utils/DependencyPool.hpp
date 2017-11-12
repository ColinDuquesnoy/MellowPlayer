#pragma once

#include <memory>
#include "fakeit.hpp"

#include <MellowPlayer/Domain/ICommandLineParser.hpp>
#include <MellowPlayer/Domain/IDeprecatedQtApplication.hpp>
#include <MellowPlayer/Domain/Notifications/INotificationPresenter.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>

class InMemoryListeningHistoryDataProvider;

namespace MellowPlayer::Domain
{
    class CurrentPlayer;
    class IPlayer;
    class IWorkDispatcher;
    class INotificationPresenter;
    class ListeningHistory;
    class Players;
    class Settings;
    class StreamingServicesController;
    class Updater;
    class AbstractPlatformUpdater;
}

namespace MellowPlayer::Infrastructure
{
    class LocalAlbumArt;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel;
    class StreamingServicesControllerViewModel;
    class ThemeViewModel;
    class UpdaterViewModel;
    class MainWindowViewModel;
    class Notifier;
}

namespace MellowPlayer::Tests
{
    class DependencyPool
    {
    public:
        DependencyPool();
        ~DependencyPool();

        // Mock Objects
        fakeit::Mock<Domain::INotificationPresenter>& getNotificationPresenterMock();

        // Domain Layer
        Domain::StreamingServicesController& getStreamingServicesController();
        Domain::IPlayer& getCurrentPlayer();
        Domain::Players& getPlayers();
        Domain::IStreamingServiceCreator& getStreamingServicesCreator();
        Domain::ISettingsStore& getSettingsStore();
        Domain::Settings& getSettings();
        Domain::ICommandLineParser& getCommandLineParser();
        Domain::IWorkDispatcher& getWorkDispatcher();
        Domain::ListeningHistory& getListeningHistory();
        Domain::Updater& getUpdater();
        Domain::IDeprecatedQtApplication& getQtApplication();
        Domain::INotificationPresenter& getNotificationPresenter();
        Domain::AbstractPlatformUpdater& getPlatformUpdater();
        Domain::IUserScriptFactory& getUserScriptFactory();

        // Infrastructure layer
        Infrastructure::LocalAlbumArt& getLocalAlbumArt();

        // Presentation Layer
        Presentation::Notifier& getNotifier();
        Presentation::StreamingServicesControllerViewModel& getStreamingServicesControllerViewModel();
        Presentation::ListeningHistoryViewModel& getListeningHistoryViewModel();
        Presentation::ThemeViewModel& getThemeViewModel();
        Presentation::UpdaterViewModel& getUpdaterViewModel();
        Presentation::MainWindowViewModel& getMainWindowViewModel();

    private:
        // mocks
        fakeit::Mock<Domain::ICommandLineParser> mICommandLineParser;
        fakeit::Mock<Domain::IDeprecatedQtApplication> mIQtApplication;
        fakeit::Mock<Domain::ISettingsStore> mISettingsStore;
        fakeit::Mock<Domain::IStreamingServiceCreator> mIStreamingServiceCreator;
        fakeit::Mock<Domain::INotificationPresenter> mINotificationPresenter;
        fakeit::Mock<Domain::IUserScriptFactory> mUserScriptsFactoryMock;

        // app
        std::unique_ptr<Domain::CurrentPlayer> pCurrentPlayer;
        std::unique_ptr<Domain::ListeningHistory> pListeningHistory;
        std::unique_ptr<Domain::Players> pPlayers;
        std::unique_ptr<Domain::Settings> pSettings;
        std::unique_ptr<Domain::StreamingServicesController> pStreamingServicesController;
        std::unique_ptr<Domain::Updater> pUpdater;
        std::unique_ptr<Domain::AbstractPlatformUpdater> pPlatformUpdater;

        // infra
        std::unique_ptr<Infrastructure::LocalAlbumArt> pLocalAlbumArt;

        // presentation
        std::unique_ptr<Presentation::ListeningHistoryViewModel> pListeningHistoryViewModel;
        std::unique_ptr<Presentation::StreamingServicesControllerViewModel> pStreamingServicesControllerViewModel;
        std::unique_ptr<Presentation::ThemeViewModel> pThemeViewModel;
        std::unique_ptr<Presentation::UpdaterViewModel> pUpdaterViewModel;
        std::unique_ptr<Presentation::MainWindowViewModel> pMainWindowViewModel;
        std::unique_ptr<Presentation::Notifier> pNotifier;

        std::unique_ptr<InMemoryListeningHistoryDataProvider> dataProvider;
    };
}
