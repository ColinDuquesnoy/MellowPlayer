#pragma once

#include <boost/di.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Application/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Application/ListeningHistory/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Application/Notifications/INotifier.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifier.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/ViewModels/StyleViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <MellowPlayer/Infrastructure/Utils/AlbumArt/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/Utils/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Applications/CoreApplication.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Infrastructure/Controllers/HotkeysController.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArt.hpp>

#ifdef USE_LIBNOTIFY
    #include <MellowPlayer/Presentation/Notifications/Presenters/LibnotifyPresenter.hpp>
#endif

#ifdef Q_OS_LINUX
    #include <MellowPlayer/Infrastructure/Platform/Linux/MprisController.hpp>
    #include <MellowPlayer/Infrastructure/Platform/Linux/LinuxApplication.hpp>
#endif


USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)

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
        di::bind<IStreamingServiceLoader>().to<StreamingServiceLoader>().in(scope),
        di::bind<IPlayer>().in(di::singleton).to<CurrentPlayer>(),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<IMainWindow>().to<MellowPlayer::Presentation::MainWindowViewModel>().in(scope),
        di::bind<ILocalAlbumArt>().to<LocalAlbumArt>().in(scope),
        di::bind<IHotkeysController>().to<HotkeysController>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<IListeningHistoryDataProvider>().to<SqlLiteListeningHistoryDataProvider>().in(scope),
        di::bind<INotifier>().to<Notifier>().in(scope),
        di::bind<ISettingsProvider>().to<QSettingsProvider>().in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope)
    );
};

auto platformInjector = [](ScopedScope& scope) {
#ifdef Q_OS_LINUX
    return di::make_injector(
            di::bind<IMprisController>().to<MprisController>().in(scope),
            di::bind<IApplication>().to<LinuxApplication>().in(scope)
    );
#else
    return di::make_injector(
        di::bind<IApplication>().to<CoreApplication>().in(scope)
    );
#endif
};

auto notificationPresenterInjector = [](ScopedScope& scope) {
#if defined(USE_LIBNOTIFY)
    return di::make_injector(
            di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(scope)
    );
#else
    return di::make_injector(
            di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>().in(scope)
    );
#endif
};
