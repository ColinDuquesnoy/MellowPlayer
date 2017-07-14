#pragma once

#include <boost/di.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Application/Notifications/INotifier.hpp>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifier.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <MellowPlayer/Infrastructure/Controllers/HotkeysController.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/Utils/AlbumArt/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>
#include <Mocks/LocalAlbumArtMock.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>
#include <Mocks/StreamingServiceCreatorMock.hpp>

#ifdef USE_LIBNOTIFY
#include <MellowPlayer/Presentation/Notifications/Presenters/LibnotifyPresenter.hpp>
#endif


#ifdef Q_OS_LINUX
#include <MellowPlayer/Infrastructure/Platform/Linux/MprisController.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/LinuxApplication.hpp>
#endif

#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/SettingsProviderMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/NotificationPresenterMock.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <Mocks/CommnandLineParserMock.hpp>
#include <Mocks/ThemeLoaderMock>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

namespace di = boost::di;

/**
 * http://boost-experimental.github.io/di/extensions/index.html#scoped-scope
 */
class ScopedScope {
public:
    template <class, class T>
    class scope {
    public:
        template <class T_>
        using is_referable = typename di::wrappers::shared<ScopedScope, T>::template is_referable<T_>;

        template <class, class, class TProvider, class T_ = di::aux::decay_t<decltype(di::aux::declval<TProvider>().get())>>
        static decltype(di::wrappers::shared<ScopedScope, T_>{
            std::shared_ptr<T_>{std::shared_ptr<T_>{di::aux::declval<TProvider>().get()}}})
        try_create(const TProvider &);

        template <class T_, class, class TProvider>
        auto create(const TProvider &provider) {
            return create_impl<di::aux::decay_t<decltype(provider.get())>>(provider);
        }

        scope() = default;
        scope(scope &&other) noexcept : object_(other.object_) { other.object_ = nullptr; }
        ~scope() noexcept { delete object_; }

    private:
        template <class, class TProvider>
        auto create_impl(const TProvider &provider) {
            if (!object_) {
                object_ = new std::shared_ptr<T>{provider.get()};
            }
            return di::wrappers::shared<ScopedScope, T, std::shared_ptr<T> &>{*object_};
        }

        std::shared_ptr<T> *object_ = nullptr;
    };
};

static auto hotkeysControllerMock = HotkeysControllerMock::get();
static auto mainWindowMock = MainWindowMock::get();
static auto qtApplicationMock = QtApplicationMock::get();
static auto streamingServiceLoaderMock = StreamingServiceLoaderMock::get();
static auto systemTrayIconMock = SystemTrayIconMock::get();
static auto notificationPresenterMock = NotificationPresenterMock::get();
static auto localAlbumArtMock = LocalAlbumArtMock::getMockWithUrlOk();
static auto streamingServiceCreatorMock = StreamingServiceCreatorMock::get();
static auto streamingServiceWatcherMock = StreamingServiceWatcherMock::get();
static auto commandLineParserMock = CommandLineParserMock::get();
static auto themeLoaderMock = ThemeLoaderMock::get();

inline auto getTestInjector(ScopedScope& scope) {
    static auto settingsProviderMock = SettingsProviderMock::get();
    static InMemoryListeningHistoryDataProvider dataProvider;
    static FakeWorkDispatcher workDispatcher;

    return di::make_injector(
        di::bind<IStreamingServiceLoader>().to(streamingServiceLoaderMock.get()),
        di::bind<IPlayer>().to<CurrentPlayer>().in(scope),
        di::bind<INotificationPresenter>().to(notificationPresenterMock.get()),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloaderMock>().in(scope),
        di::bind<IMainWindow>().to(mainWindowMock.get()),
        di::bind<IHotkeysController>().to(hotkeysControllerMock.get()),
        di::bind<IQtApplication>().to(qtApplicationMock.get()),
        di::bind<ISettingsProvider>().to(settingsProviderMock.get()),
        di::bind<ISystemTrayIcon>().to(systemTrayIconMock.get()),
        di::bind<ILocalAlbumArt>().to(localAlbumArtMock.get()),
        di::bind<IListeningHistoryDataProvider>().to(dataProvider),
        di::bind<IWorkDispatcher>().to(workDispatcher),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope),
        di::bind<IStreamingServiceCreator>().to(streamingServiceCreatorMock.get()),
        di::bind<IStreamingServiceWatcher>().to(streamingServiceWatcherMock.get()),
        di::bind<ICommandLineParser>().to(commandLineParserMock.get()),
        di::bind<IThemeLoader>().to(themeLoaderMock.get())
    );
};

