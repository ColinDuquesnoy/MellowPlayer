#pragma once
#include <boost/di.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <MellowPlayer/Infrastructure.hpp>

#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/HotkeysServiceMock.hpp>
#include <Mocks/MainWindowMock.hpp>
#include <Mocks/MprisServiceMock.hpp>
#include <Mocks/PlayerMock.hpp>
#include <Mocks/QtApplicationMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>

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

auto getTestInjector = [](ScopedScope& scope) {

    static auto hotkeysServiceMock = HotkeysServiceMock::get();
    static auto mainWindowMock = MainWindowMock::get();
    static auto playerMock = PlayerMock::get();
    static auto qtApplicationMock = QtApplicationMock::get();
    static auto streamingServiceLoaderMock = StreamingServiceLoaderMock::get();

    streamingServiceLoaderMock.get().load();


    return di::make_injector(
        di::bind<IStreamingServicesLoader>().to(streamingServiceLoaderMock.get()),
        di::bind<IPlayer>().to<PlayerProxy>().in(scope),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloaderMock>().in(scope),
        di::bind<IMainWindow>().to(mainWindowMock.get()),
        di::bind<IHotkeysService>().to(hotkeysServiceMock.get()),
        di::bind<IQtApplication>().to(qtApplicationMock.get())
    );
};

