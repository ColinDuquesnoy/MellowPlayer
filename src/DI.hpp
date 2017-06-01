#pragma once

#include <boost/di.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <MellowPlayer/Application/Interfaces/IStreamingServicePluginLoader.hpp>
#include <MellowPlayer/Application/Interfaces/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/Settings/ISettingsSchemaLoader.hpp>
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
#include <MellowPlayer/Infrastructure/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServicePluginLoader.hpp>
#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Applications/CoreApplication.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/SqlLiteListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Infrastructure/Services/HotkeysService.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArtService.hpp>

#ifdef USE_SNORENOTIFY
    #include <MellowPlayer/Presentation/Notifications/Presenters/SnorenotifyPresenter.hpp>
#endif

#ifdef Q_OS_LINUX
    #include <MellowPlayer/Infrastructure/Services/MprisService.hpp>
    #include <MellowPlayer/Infrastructure/Applications/LinuxApplication.hpp>
#endif


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

auto defaultInjector = [](ScopedScope& scope) {
    return di::make_injector(
        di::bind<IStreamingServicePluginLoader>().to<StreamingServicePluginLoader>().in(scope),
        di::bind<IPlayer>().in(di::singleton).to<PlayerProxy>(),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<IMainWindow>().to<MellowPlayer::Presentation::MainWindowModel>().in(scope),
        di::bind<ILocalAlbumArtService>().to<LocalAlbumArtService>().in(scope),
        di::bind<IHotkeysService>().to<HotkeysService>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<IListeningHistoryDataProvider>().to<SqlLiteListeningHistoryDataProvider>().in(scope),
        di::bind<INotificationService>().to<NotificationService>().in(scope),
        di::bind<ISettingsProvider>().to<QSettingsProvider>().in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope)
    );
};

auto platformInjector = [](ScopedScope& scope) {
#ifdef Q_OS_LINUX
    return di::make_injector(
            di::bind<IMprisService>().to<MprisService>().in(scope),
            di::bind<IApplication>().to<LinuxApplication>().in(scope)
    );
#else
    return di::make_injector(
        di::bind<IApplication>().to<CoreApplication>().in(scope)
    );
#endif
};

auto notificationPresenterInjector = [](ScopedScope& scope) {
#if defined(USE_SNORENOTIFY)
    return di::make_injector(
        di::bind<INotificationPresenter>().to<SnorenotifyPresenter>().in(scope)
    );
#elif defined(USE_LIBNOTIFY)
    return di::make_injector(
            di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(scope)
    );
#else
    return di::make_injector(
            di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>().in(scope)
    );
#endif
};
