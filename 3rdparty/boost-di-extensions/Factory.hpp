//
// Copyright (c) 2012-2017 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// taken from https://raw.githubusercontent.com/boost-experimental/di/cpp14/extension/injections/factory.cpp and
// adapted to fit our coding conventions
#pragma once

#include <cassert>
#include <memory>
#include <boost/di.hpp>

namespace di = boost::di;


template <class T, class... TArgs>
struct IFactory {
    virtual ~IFactory() noexcept = default;
    virtual std::unique_ptr<T> create(TArgs&&...) const = 0;
};

template <class, class, class>
struct factory_impl;

template <class TInjector, class T, class I, class... TArgs>
struct factory_impl<TInjector, T, IFactory<I, TArgs...>> : IFactory<I, TArgs...> {
    explicit factory_impl(const TInjector& injector) : injector_((TInjector&)injector) {}

    std::unique_ptr<I> create(TArgs&&... args) const override {
        // clang-format off
        auto injector = di::make_injector(
                std::move(injector_)
#if (__clang_major__ == 3) && (__clang_minor__ > 4) || defined(__GCC___) || defined(__MSVC__)
                , di::bind<TArgs>().to(std::forward<TArgs>(args))[di::override]...
#else // wknd for clang 3.4
                , di::core::dependency<di::scopes::instance, TArgs, TArgs, di::no_name, di::core::override>(std::forward<TArgs>(args))...
#endif
        );
        // clang-format on

        auto object = injector.template create<std::unique_ptr<T>>();
        injector_ = std::move(injector);
        return std::move(object);
    }

private:
    TInjector& injector_;
};

template <class T>
struct Factory {
    template <class TInjector, class TDependency>
    auto operator()(const TInjector& injector, const TDependency&) const {
        static auto sp = std::make_shared<factory_impl<TInjector, T, typename TDependency::expected>>(injector);
        return sp;
    }
};
