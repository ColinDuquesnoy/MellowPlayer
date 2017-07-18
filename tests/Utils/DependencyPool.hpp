#pragma once

#include "fakeit/fakeit.hpp"

#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Presentation/IQtApplication.hpp>
#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>

class InMemoryListeningHistoryDataProvider;

namespace MellowPlayer::Application {
    class CurrentPlayer;
    class IPlayer;
    class IWorkDispatcher;
    class INotificationPresenter;
    class ListeningHistory;
    class Players;
    class Settings;
    class StreamingServicesController;
    class Updater;
}

namespace MellowPlayer::Infrastructure {
    class LocalAlbumArt;
}

namespace MellowPlayer::Presentation {
    class ListeningHistoryViewModel;
    class StreamingServicesControllerViewModel;
    class ThemeViewModel;
    class UpdaterViewModel;
    class MainWindowViewModel;
    class Notifier;
}

namespace MellowPlayer::Tests {

    class DependencyPool {
    public:
        DependencyPool();
        ~DependencyPool();

        // Mock Objects
        fakeit::Mock<Application::INotificationPresenter>& getNotificationPresenterMock();

        // Application Layer
        Application::StreamingServicesController& getStreamingServicesController();
        Application::IPlayer& getCurrentPlayer();
        Application::Players& getPlayers();
        Application::IStreamingServiceCreator& getStreamingServicesCreator();
        Application::ISettingsProvider& getSettingsProvider();
        Application::Settings& getSettings();
        Application::ICommandLineParser& getCommandLineParser();
        Application::IWorkDispatcher& getWorkDispatcher();
        Application::ListeningHistory& getListeningHistory();
        Application::Updater& getUpdater();
        Application::IQtApplication& getQtApplication();
        Application::INotificationPresenter& getNotificationPresenter();

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
        fakeit::Mock<Application::ICommandLineParser> mICommandLineParser;
        fakeit::Mock<Application::IQtApplication> mIQtApplication;
        fakeit::Mock<Application::ISettingsProvider> mISettingsProvider;
        fakeit::Mock<Application::IStreamingServiceCreator> mIStreamingServiceCreator;
        fakeit::Mock<Application::INotificationPresenter> mINotificationPresenter;

        // app
        std::unique_ptr<Application::CurrentPlayer> pCurrentPlayer;
        std::unique_ptr<Application::ListeningHistory> pListeningHistory;
        std::unique_ptr<Application::Players> pPlayers;
        std::unique_ptr<Application::Settings> pSettings;
        std::unique_ptr<Application::StreamingServicesController> pStreamingServicesController;
        std::unique_ptr<Application::Updater> pUpdater;

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
