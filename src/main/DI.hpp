#pragma once

#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Presentation/Mpris/IMprisService.hpp>
#include <MellowPlayer/Presentation/Mpris/NullMprisService.hpp>
#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/Updater/Github/LatestGithubReleaseQuerier.hpp>
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Updater/ILatestReleaseQuerier.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/SingleInstance.hpp>
#include <MellowPlayer/Infrastructure/Application/WithLogging.hpp>
#include <MellowPlayer/Infrastructure/Application/WithCommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/CommandLineArguments.hpp>
#include <MellowPlayer/Presentation/Hotkeys/IHotkeys.hpp>
#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>
#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDatabase.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/DelayedListeningHistory.hpp>
#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <MellowPlayer/Infrastructure/Network/HttpClient.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/Application.hpp>
#include <MellowPlayer/Infrastructure/Timer.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <boost/di.hpp>
#include <boost/di/extension/scopes/scoped.hpp>
#include <boost-di-extensions/Factory.hpp>

#ifdef USE_LIBNOTIFY
    #include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyPresenter.hpp>
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#include <MellowPlayer/Presentation/Mpris/Linux/MprisService.hpp>
#include <MellowPlayer/Infrastructure/Updater/Linux/LinuxUpdater.hpp>
#elif defined(Q_OS_WIN)
    #include <MellowPlayer/Infrastructure/Updater/Windows/WindowsUpdater.hpp>
#elif defined(Q_OS_OSX)
    #include <MellowPlayer/Infrastructure/Updater/OSX/OSXUpdater.hpp>
#endif

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

namespace di = boost::di;


struct ApplicationFactory {
    template <class TInjector, class TDependency>
    auto operator()(const TInjector& const_injector, const TDependency&) {
        if (object_ == nullptr) {
            auto& injector = const_cast<TInjector&>(const_injector);

            IQtApplication& qtApplication = injector.template create<IQtApplication&>();
            ICommandLineArguments& commandLineArguments = injector.template create<ICommandLineArguments&>();

            auto baseApplication = make_shared<Application>(qtApplication);

            IPlayer& player = injector.template create<IPlayer&>();
            IFactory<ILocalServer, QString>& localServerFactory = injector.template create<IFactory<ILocalServer, QString>&>();
            IFactory<ILocalSocket>& localSocketFactory = injector.template create<IFactory<ILocalSocket>&>();

            auto singleInstance = make_shared<SingleInstance>(baseApplication, qtApplication, player,
                                                              commandLineArguments, localServerFactory,
                                                              localSocketFactory);
            auto withLogging = make_shared<WithLogging>(singleInstance, commandLineArguments);

            object_ = make_shared<WithCommandLineArguments>(withLogging, commandLineArguments);
        }
        return object_;
    }

private:
    std::shared_ptr<IApplication> object_ = nullptr;
};

// clang-format off
auto defaultInjector = [](di::extension::detail::scoped& scope) {
    return di::make_injector(
        di::bind<IApplication>().to(ApplicationFactory { }),
        di::bind<IQtApplication>().to<QtApplication>().in(scope),
        di::bind<IQmlApplicationEngine>().to<QmlApplicationEngine>().in(scope),
        di::bind<IContextProperties>().to<ContextProperties>().in(scope),
        di::bind<IPlayer>().in(di::singleton).to<CurrentPlayer>(),
        di::bind<ICommandLineArguments>().to<CommandLineArguments>(),
        di::bind<IFactory<ILocalSocket>>().to(Factory<LocalSocket> { }),
        di::bind<IFactory<ILocalServer, QString>>().to(Factory<LocalServer> { }),
        di::bind<IStreamingServiceLoader>().to<StreamingServiceLoader>().in(scope),
        di::bind<IStreamingServiceWatcher>().to<StreamingServiceWatcher>().in(scope),
        di::bind<ILoggerFactory>().to<SpdLoggerFactory>().in(scope),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<ILocalAlbumArt>().to<LocalAlbumArt>().in(scope),
        di::bind<IHotkeys>().to<Hotkeys>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<IListeningHistoryDatabase>().to<SqlLiteListeningHistoryDatabase>().in(scope),
        di::bind<ISettingsStore>().to<QSettingsStore>().in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope),
        di::bind<IStreamingServiceCreator>().to<StreamingServiceCreator>().in(scope),
        di::bind<IThemeLoader>().to<ThemeLoader>().in(scope),
        di::bind<ILatestReleaseQuerier>().to<LatestGithubReleaseQuerier>().in(scope),
        di::bind<IHttpClient>().to<HttpClient>().in(scope),
        di::bind<IFileDownloader>().to<FileDownloader>().in(scope),
        di::bind<IUserScriptFactory>().to<UserScriptFactory>().in(scope),
        di::bind<IMainWindow>().to<MainWindowViewModel>().in(scope),
        di::bind<INotifications>().to<Notifications>().in(scope),
        di::bind<IViewModels>().to<ViewModels>().in(scope),
        di::bind<INetworkProxies>().to<NetworkProxies>().in(scope),
        di::bind<ITimer>().to<Timer>().in(di::unique),
        di::bind<IListeningHistory>().to<DelayedListeningHistory>().in(scope)
    );
};

auto platformInjector = [](di::extension::detail::scoped& scope) {
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    return di::make_injector(
        di::bind<IMprisService>().to<MprisService>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<LinuxUpdater>().in(scope)
    );
#elif defined(Q_OS_WIN)
    return di::make_injector(
        di::bind<IMprisService>().to<NullMprisService>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<WindowsUpdater>().in(scope)
    );
#elif defined(Q_OS_OSX)
    return di::make_injector(
        di::bind<IMprisService>().to<NullMprisService>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<OSXUpdater>().in(scope)
    );
#endif
};

auto notificationPresenterInjector = [](di::extension::detail::scoped& scope) {
#if defined(USE_LIBNOTIFY)
    return di::make_injector(di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(scope));
#else
    return di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>().in(scope));
#endif
};

// clang-format on
