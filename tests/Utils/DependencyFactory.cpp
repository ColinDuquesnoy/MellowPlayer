#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Updater/Github/GithubReleaseQuerier.hpp>

#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>

#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>

#include <Mocks/StreamingServiceCreatorMock.hpp>
#include <Mocks/SettingsProviderMock.hpp>
#include <Mocks/CommnandLineParserMock.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/ThemeLoaderMock>
#include <Mocks/FakeHttpClient.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include "Mocks/StreamingServiceLoaderMock.hpp"
#include "Mocks/StreamingServiceWatcherMock.hpp"

#include "DependencyFactory.hpp"

using namespace fakeit;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Tests;

StreamingServicesController& DependencyFactory::createStreamingServicesController() {
    static auto streamingServiceLoaderMock = StreamingServiceLoaderMock::get();
    static auto streamingServiceWatcherMock = StreamingServiceWatcherMock::get();
    pStreamingServicesController = make_unique<StreamingServicesController>(streamingServiceLoaderMock.get(), streamingServiceWatcherMock.get());
    return *pStreamingServicesController;
}

StreamingServicesControllerViewModel& DependencyFactory::createStreamingServicesControllerViewModel() {
    pStreamingServicesControllerViewModel = make_unique<StreamingServicesControllerViewModel>(
            createStreamingServicesController(), createPlayers(), createSettings(), createWorkDispatcher(),
            createStreamingServicesCreator(), createCommandLineParser());
    return *pStreamingServicesControllerViewModel;
}

Players& DependencyFactory::createPlayers() {
    pPlayers = make_unique<Players>(createStreamingServicesController());
    return *pPlayers;
}

IStreamingServiceCreator& DependencyFactory::createStreamingServicesCreator() {
    return mIStreamingServiceCreator.get();
}

ISettingsProvider& DependencyFactory::createSettingsProvider() {
    return mISettingsProvider.get();
}

Settings& DependencyFactory::createSettings() {
    static SettingsSchemaLoader loader;
    pSettings = make_unique<Settings>(loader, createSettingsProvider());
    return *pSettings;
}

ICommandLineParser& DependencyFactory::createCommandLineParser() {
    return mICommandLineParser.get();
}

IWorkDispatcher& DependencyFactory::createWorkDispatcher() {
    static FakeWorkDispatcher instance;
    return instance;
}

ListeningHistoryViewModel& DependencyFactory::createListeningHistoryViewModel() {
    pListeningHistoryViewModel = make_unique<ListeningHistoryViewModel>(createListeningHistory());
    return *pListeningHistoryViewModel;
}

ListeningHistory& DependencyFactory::createListeningHistory() {
    static InMemoryListeningHistoryDataProvider dataProvider;
    pListeningHistory = make_unique<ListeningHistory>(dataProvider, createCurrentPlayer(), createWorkDispatcher(),
                                                      createSettings());
    return *pListeningHistory;
}

IPlayer& DependencyFactory::createCurrentPlayer() {
    pCurrentPlayer = make_unique<CurrentPlayer>(createPlayers(), createStreamingServicesController());
    return *pCurrentPlayer;
}

ThemeViewModel& DependencyFactory::createThemeViewModel() {
    static auto mock = ThemeLoaderMock::get();
    pThemeViewModel = make_unique<ThemeViewModel>(createStreamingServicesController(), createSettings(), mock.get());
    return *pThemeViewModel;
}

UpdaterViewModel& DependencyFactory::createUpdaterViewModel() {
    pUpdaterViewModel = make_unique<UpdaterViewModel>(createUpdater());
    return *pUpdaterViewModel;
}

Updater& DependencyFactory::createUpdater() {
    static FakeHttpClient httpClient;
    static GithubReleaseQuerier querier(httpClient);
    pUpdater = make_unique<Updater>(querier, createSettings());
    return *pUpdater;
}

IQtApplication& DependencyFactory::createQtApplication() {
    return mIQtApplication.get();
}

MainWindowViewModel& DependencyFactory::createMainWindowViewModel() {
    pMainWindowViewModel = make_unique<MainWindowViewModel>(
            createStreamingServicesControllerViewModel(), createListeningHistoryViewModel(), createThemeViewModel(),
            createUpdaterViewModel(), createQtApplication(), createCurrentPlayer(), createSettings());
    return *pMainWindowViewModel;
}

DependencyFactory::DependencyFactory():
        mICommandLineParser(CommandLineParserMock::get()),
        mIQtApplication(QtApplicationMock::get()),
        mISettingsProvider(SettingsProviderMock::get()),
        mIStreamingServiceCreator(StreamingServiceCreatorMock::get()) {

}

