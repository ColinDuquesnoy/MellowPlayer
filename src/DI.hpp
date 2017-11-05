#pragma once

#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/IMpris.hpp>
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/Notifications/INotifier.hpp>
#include <MellowPlayer/Domain/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Domain/Updater/Github/LatestGithubReleaseQuerier.hpp>
#include <MellowPlayer/Domain/Updater/IHttpClient.hpp>
#include <MellowPlayer/Domain/Updater/ILatestReleaseQuerier.hpp>
#include <MellowPlayer/Domain/Updater/Updater.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/Applications/CoreApplication.hpp>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Hotkeys/IHotkeys.hpp>
#include <MellowPlayer/Infrastructure/Hotkeys/Hotkeys.hpp>
#include <MellowPlayer/Infrastructure/FileDownloader.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <MellowPlayer/Infrastructure/Updater/HttpClient.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifier.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <boost/di.hpp>

#ifdef USE_LIBNOTIFY
#include <MellowPlayer/Presentation/Notifications/Presenters/LibnotifyPresenter.hpp>
#endif

#if defined(Q_OS_LINUX)
#include <MellowPlayer/Infrastructure/Platform/Linux/LinuxApplication.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/Mpris.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/Updater/LinuxUpdater.hpp>
#elif defined(Q_OS_WIN)
#include <MellowPlayer/Infrastructure/Platform/Windows/Updater/WindowsUpdater.hpp>
#elif defined(Q_OS_OSX)
#include <MellowPlayer/Infrastructure/Platform/OSX/Updater/OSXUpdater.hpp>
#endif

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

namespace di = boost::di;

/*<<ScopedScope extension>>*/
/**
 * http://boost-experimental.github.io/di/extensions/index.html#scoped-scope
 */
class ScopedScope
{
public:
    template <class, class T>
    class scope
    {
    public:
        template <class T_>
        using is_referable = typename di::wrappers::shared<ScopedScope, T>::template is_referable<T_>;

        template <class, class, class TProvider, class T_ = di::aux::decay_t<decltype(di::aux::declval<TProvider>().get())>>
        static decltype(di::wrappers::shared<ScopedScope, T_>{std::shared_ptr<T_>{std::shared_ptr<T_>{di::aux::declval<TProvider>().get()}}})
        try_create(const TProvider&);

        template <class T_, class, class TProvider>
        auto create(const TProvider& provider)
        {
            return create_impl<di::aux::decay_t<decltype(provider.get())>>(provider);
        }

        scope() = default;
        scope(scope&& other) noexcept : object_(other.object_)
        {
            other.object_ = nullptr;
        }
        ~scope() noexcept
        {
            delete object_;
        }

    private:
        template <class, class TProvider>
        auto create_impl(const TProvider& provider)
        {
            if (!object_) {
                object_ = new std::shared_ptr<T>{provider.get()};
            }
            return di::wrappers::shared<ScopedScope, T, std::shared_ptr<T>&>{*object_};
        }

        std::shared_ptr<T>* object_ = nullptr;
    };
};

// clang-format off
auto defaultInjector = [](ScopedScope &scope) {
    return di::make_injector(
        di::bind<IStreamingServiceLoader>().to<StreamingServiceLoader>().in(scope),
        di::bind<IPlayer>().in(di::singleton).to<CurrentPlayer>(),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<IMainWindow>().to<MellowPlayer::Presentation::MainWindowViewModel>().in(scope),
        di::bind<ILocalAlbumArt>().to<LocalAlbumArt>().in(scope),
        di::bind<MellowPlayer::Infrastructure::IHotkeys>().to<Hotkeys>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<IListeningHistoryDataProvider>().to<SqlLiteListeningHistoryDataProvider>().in(scope),
        di::bind<INotifier>().to<Notifier>().in(scope),
        di::bind<ISettingsStore>().to<QSettingsStore>().in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope),
        di::bind<IStreamingServiceCreator>().to<StreamingServiceCreator>().in(scope),
        di::bind<IStreamingServiceWatcher>().to<StreamingServiceWatcher>().in(scope),
        di::bind<IThemeLoader>().to<ThemeLoader>().in(scope),
        di::bind<ILatestReleaseQuerier>().to<LatestGithubReleaseQuerier>().in(scope),
        di::bind<IHttpClient>().to<HttpClient>().in(scope),
        di::bind<IFileDownloader>().to<FileDownloader>().in(scope),
        di::bind<IUserScriptFactory>().to<UserScriptFactory>().in(scope)
    );
};

auto platformInjector = [](ScopedScope &scope) {
#if defined(Q_OS_LINUX)
    return di::make_injector(
        di::bind<IMpris>().to<Mpris>().in(scope),
        di::bind<IApplication>().to<LinuxApplication>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<LinuxUpdater>().in(scope)
    );
#elif defined(Q_OS_WIN)
    return di::make_injector(
        di::bind<IApplication>().to<CoreApplication>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<WindowsUpdater>().in(scope)
    );
#elif defined(Q_OS_OSX)
    return di::make_injector(
        di::bind<IApplication>().to<CoreApplication>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<OSXUpdater>().in(scope)
    );
#endif
};

auto notificationPresenterInjector = [](ScopedScope &scope) {
#if defined(USE_LIBNOTIFY)
    return di::make_injector(di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(scope));
#else
    return di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>().in(scope));
#endif
};

// clang-format on
