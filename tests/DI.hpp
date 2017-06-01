#pragma once

#include <boost/di.hpp>
#include <MellowPlayer/Application/Interfaces/IStreamingServicePluginLoader.hpp>
#include <MellowPlayer/Application/Interfaces/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Interfaces/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/Application/Interfaces/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/Interfaces/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Application/Interfaces/ILocalAlbumArtService.hpp>
#include <MellowPlayer/Application/Interfaces/INotificationsService.hpp>
#include <MellowPlayer/Application/Interfaces/IHotkeysService.hpp>
#include <MellowPlayer/Application/Interfaces/IMprisService.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Player/PlayerProxy.hpp>
#include <MellowPlayer/Application/Services/PlayerService.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/Application/Services/ListeningHistoryService.hpp>
#include <MellowPlayer/Presentation/Notifications/NotificationService.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/LibnotifyPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SnorenotifyPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceStyleModel.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp>
#include <MellowPlayer/Presentation/Models/MainWindowModel.hpp>
#include <MellowPlayer/Presentation/SystemTrayIcon.hpp>
#include <MellowPlayer/Infrastructure/Services/HotkeysService.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArtService.hpp>
#include <MellowPlayer/Infrastructure/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServicePluginLoader.hpp>
#include <MellowPlayer/Infrastructure/SqlLiteListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>
#include <Mocks/LocalAlbumArtServiceMock.hpp>
#include <Mocks/InMemoryListeningHistoryDataProvider.hpp>
#include <Mocks/FakeWorkDispatcher.hpp>

#ifdef USE_SNORENOTIFY
#include <MellowPlayer/Presentation/Notifications/Presenters/SnorenotifyPresenter.hpp>
#endif

#ifdef Q_OS_LINUX
#include <MellowPlayer/Infrastructure/Services/MprisService.hpp>
#include <MellowPlayer/Infrastructure/Applications/LinuxApplication.hpp>
#endif

#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/SettingsProviderMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/NotificationPresenterMock.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/PluginLoaderMock.hpp>
#include <Mocks/SystemTrayIconMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

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

static auto hotkeysServiceMock = HotkeysServiceMock::get();
static auto mainWindowMock = MainWindowMock::get();
static auto qtApplicationMock = QtApplicationMock::get();
static auto pluginLoaderMock = PluginLoaderMock::get();
static auto systemTrayIconMock = SystemTrayIconMock::get();
static auto notificationPresenterMock = NotificationPresenterMock::get();
static auto localAlbumArtServiceMock = LocalAlbumArtServiceMock::getMockWithUrlOk();

inline auto getTestInjector(ScopedScope& scope) {
    static auto settingsProviderMock = SettingsProviderMock::get();
    static InMemoryListeningHistoryDataProvider dataProvider;
    static FakeWorkDispatcher workDispatcher;

    return di::make_injector(
        di::bind<IStreamingServicePluginLoader>().to(pluginLoaderMock.get()),
        di::bind<IPlayer>().to<PlayerProxy>().in(scope),
        di::bind<INotificationPresenter>().to(notificationPresenterMock.get()),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloaderMock>().in(scope),
        di::bind<IMainWindow>().to(mainWindowMock.get()),
        di::bind<IHotkeysService>().to(hotkeysServiceMock.get()),
        di::bind<IQtApplication>().to(qtApplicationMock.get()),
        di::bind<ISettingsProvider>().to(settingsProviderMock.get()),
        di::bind<ISystemTrayIcon>().to(systemTrayIconMock.get()),
        di::bind<ILocalAlbumArtService>().to(localAlbumArtServiceMock.get()),
        di::bind<IListeningHistoryDataProvider>().to(dataProvider),
        di::bind<IWorkDispatcher>().to(workDispatcher),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope)
    );
};

