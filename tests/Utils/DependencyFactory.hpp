#pragma once

#include "fakeit/fakeit.hpp"

namespace MellowPlayer::Application {
    class CurrentPlayer;
    class ICommandLineParser;
    class IPlayer;
    class IQtApplication;
    class ISettingsProvider;
    class IStreamingServiceCreator;
    class IWorkDispatcher;
    class ListeningHistory;
    class Players;
    class Settings;
    class StreamingServicesController;
    class Updater;
}

namespace MellowPlayer::Presentation {
    class ListeningHistoryViewModel;
    class StreamingServicesControllerViewModel;
    class ThemeViewModel;
    class UpdaterViewModel;
    class MainWindowViewModel;
}

namespace MellowPlayer::Tests {

    class DependencyFactory {
    public:
        DependencyFactory();
        // Application Layer
        Application::StreamingServicesController& createStreamingServicesController();
        Application::IPlayer& createCurrentPlayer();
        Application::Players& createPlayers();
        Application::IStreamingServiceCreator& createStreamingServicesCreator();
        Application::ISettingsProvider& createSettingsProvider();
        Application::Settings& createSettings();
        Application::ICommandLineParser& createCommandLineParser();
        Application::IWorkDispatcher& createWorkDispatcher();
        Application::ListeningHistory& createListeningHistory();
        Application::Updater& createUpdater();
        Application::IQtApplication& createQtApplication();
        
        // Presentation Layer
        Presentation::StreamingServicesControllerViewModel& createStreamingServicesControllerViewModel();
        Presentation::ListeningHistoryViewModel& createListeningHistoryViewModel();
        Presentation::ThemeViewModel& createThemeViewModel();
        Presentation::UpdaterViewModel& createUpdaterViewModel();
        Presentation::MainWindowViewModel& createMainWindowViewModel();

    private:
        fakeit::Mock<MellowPlayer::Application::ICommandLineParser> mICommandLineParser;
        fakeit::Mock<MellowPlayer::Application::IQtApplication> mIQtApplication;
        fakeit::Mock<MellowPlayer::Application::ISettingsProvider> mISettingsProvider;
        fakeit::Mock<MellowPlayer::Application::IStreamingServiceCreator> mIStreamingServiceCreator;

        std::unique_ptr<MellowPlayer::Application::CurrentPlayer> pCurrentPlayer;
        std::unique_ptr<MellowPlayer::Application::ListeningHistory> pListeningHistory;
        std::unique_ptr<MellowPlayer::Application::Players> pPlayers;
        std::unique_ptr<MellowPlayer::Application::Settings> pSettings;
        std::unique_ptr<MellowPlayer::Application::StreamingServicesController> pStreamingServicesController;
        std::unique_ptr<MellowPlayer::Application::Updater> pUpdater;

        std::unique_ptr<MellowPlayer::Presentation::ListeningHistoryViewModel> pListeningHistoryViewModel;
        std::unique_ptr<MellowPlayer::Presentation::StreamingServicesControllerViewModel> pStreamingServicesControllerViewModel;
        std::unique_ptr<MellowPlayer::Presentation::ThemeViewModel> pThemeViewModel;
        std::unique_ptr<MellowPlayer::Presentation::UpdaterViewModel> pUpdaterViewModel;
        std::unique_ptr<MellowPlayer::Presentation::MainWindowViewModel> pMainWindowViewModel;
    };

}