#pragma once

#include <memory>
#include <fakeit/fakeit.hpp>

#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>
#include <UnitTests/Infrastructure/Network/FakeNetworkProxies.hpp>

class FakeListeningHistoryDatabase;

namespace MellowPlayer::Domain
{
    class CurrentPlayer;
    class IPlayer;
    class IWorkDispatcher;
    class ListeningHistory;
    class Players;
    class Settings;
    class StreamingServices;
}

namespace MellowPlayer::Infrastructure
{
    class LocalAlbumArt;
    class ICommandLineArguments;
    class Updater;
    class AbstractPlatformUpdater;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel;
    class StreamingServicesViewModel;
    class ThemeViewModel;
    class UpdaterViewModel;
    class Notifications;
    class INotificationPresenter;
}

namespace MellowPlayer::Tests
{
    class DependencyPool
    {
    public:
        DependencyPool();
        ~DependencyPool();

        // Mock Objects
        fakeit::Mock<Presentation::INotificationPresenter>& getNotificationPresenterMock();

        // Domain Layer
        Domain::StreamingServices& getStreamingServices();
        Domain::IPlayer& getCurrentPlayer();
        Domain::Players& getPlayers();
        Domain::IStreamingServiceCreator& getStreamingServicesCreator();
        Domain::ISettingsStore& getSettingsStore();
        Domain::Settings& getSettings();
        Domain::IWorkDispatcher& getWorkDispatcher();
        Domain::ListeningHistory& getListeningHistory();
        Domain::IUserScriptFactory& getUserScriptFactory();

        // Infrastructure layer
        Infrastructure::Updater& getUpdater();
        Infrastructure::AbstractPlatformUpdater& getPlatformUpdater();
        Infrastructure::LocalAlbumArt& getLocalAlbumArt();
        Infrastructure::ICommandLineArguments& getCommandLineArguments();
        Infrastructure::INetworkProxies& getNetworkProxies();

        // Presentation Layer
        Presentation::Notifications& getNotifier();
        Presentation::StreamingServicesViewModel& getStreamingServicesViewModel();
        Presentation::ListeningHistoryViewModel& getListeningHistoryViewModel();
        Presentation::ThemeViewModel& getThemeViewModel();
        Presentation::UpdaterViewModel& getUpdaterViewModel();
        Presentation::INotificationPresenter& getNotificationPresenter();
        Presentation::IContextProperties& getContextProperties();

    private:
        // mocks
        std::unique_ptr<Infrastructure::ICommandLineArguments> mICommandLineArgs;
        Domain::Tests::FakeSettingsStore mSettingsStore;
        fakeit::Mock<Domain::IStreamingServiceCreator> mIStreamingServiceCreator;
        fakeit::Mock<Presentation::INotificationPresenter> mINotificationPresenter;
        fakeit::Mock<Domain::IUserScriptFactory> mUserScriptsFactoryMock;

        // app
        std::unique_ptr<Domain::CurrentPlayer> pCurrentPlayer;
        std::unique_ptr<Domain::ListeningHistory> pListeningHistory;
        std::unique_ptr<Domain::Players> pPlayers;
        std::unique_ptr<Domain::Settings> pSettings;
        std::unique_ptr<Domain::StreamingServices> pStreamingServicesController;

        // infra
        std::unique_ptr<Infrastructure::LocalAlbumArt> pLocalAlbumArt;
        std::unique_ptr<Infrastructure::Updater> pUpdater;
        std::unique_ptr<Infrastructure::AbstractPlatformUpdater> pPlatformUpdater;

        // presentation
        std::unique_ptr<Presentation::ListeningHistoryViewModel> pListeningHistoryViewModel;
        std::unique_ptr<Presentation::StreamingServicesViewModel> pStreamingServicesControllerViewModel;
        std::unique_ptr<Presentation::ThemeViewModel> pThemeViewModel;
        std::unique_ptr<Presentation::UpdaterViewModel> pUpdaterViewModel;
        std::unique_ptr<Presentation::Notifications> pNotifier;

        std::unique_ptr<FakeListeningHistoryDatabase> dataProvider;

        Presentation::Tests::FakeContextProperties contextProperties_;
        Infrastructure::Tests::FakeNetworkProxies networkProxies_;
    };
}
