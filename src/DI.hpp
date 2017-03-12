#pragma once
#include <boost/di.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <MellowPlayer/UseCases.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <MellowPlayer/Infrastructure.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
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
        di::bind<IPluginLoader>().to<PluginLoader>().in(scope),
        di::bind<IPlayer>().in(di::singleton).to<PlayerProxy>(),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<IMainWindow>().to<MellowPlayer::Presentation::QmlMainWindow>().in(scope),
        di::bind<IHotkeysService>().to<HotkeysService>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<INotificationService>().to<NotificationService>().in(scope),
        di::bind<IApplicationSettings>().to<ApplicationSettings>().in(scope)
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
        di::bind<IApplication>().to<Application>().in(scope)
    );
#endif
};

auto notificationPresenterInjector = [](ScopedScope& scope) {
#ifdef USE_SNORENOTIFY
    return di::make_injector(
        di::bind<INotificationPresenter>().to<SnorenotifyPresenter>().in(scope)
    );
#else
    return di::make_injector(
            di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>().in(scope)
    );
#endif
};
