#pragma once

#include <memory>
#include <boost/di.hpp>

//<-
template <class T, class... TArgs>
struct IFactory {
    virtual ~IFactory() noexcept = default;
    virtual std::unique_ptr<T> create(TArgs&&...) = 0;
};

template <class, class, class>
struct FactoryImpl;

template <class TInjector, class T, class I, class... TArgs>
struct FactoryImpl<TInjector, T, IFactory<I, TArgs...>> : IFactory<I, TArgs...> {
    explicit FactoryImpl(const TInjector& injector) : injector_((TInjector&)injector) {}

    std::unique_ptr<I> create(TArgs&&... args) override {
        // clang-format off
        auto injector = boost::di::make_injector(
                std::move(injector_)
#if (__clang_major__ == 3) && (__clang_minor__ > 4) || defined(__GCC___) || defined(__MSVC__)
                , boost::di::bind<TArgs>().to(std::forward<TArgs>(args))[boost::di::override]...
#else // wknd for clang 3.4
                , boost::di::core::dependency<boost::di::scopes::instance, TArgs, TArgs, boost::di::no_name, boost::di::core::override>(std::forward<TArgs>(args))...
#endif
        );
        // clang-format on

        return injector.template create<std::unique_ptr<T>>();
    }

private:
    TInjector& injector_;
};

template <class T>
struct Factory {
    template <class TInjector, class TDependency>
    auto operator()(const TInjector& injector, const TDependency&) const noexcept {
        static auto sp = std::make_shared<FactoryImpl<TInjector, T, typename TDependency::expected>>(injector);
        return sp;
    }
};

